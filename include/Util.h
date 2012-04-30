/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef UTIL_H
#define UTIL_H
#include<ErrorType.h>
#include<Debug.h>
#include <vector>
enum UniqueIDType {
    STMT_ID=0,
    TXN_ID
};

enum HashFuncType {
    HASH_INT=0,
    HASH_BINARY,
};

class DllExport Util 
{
    public:
    static unsigned int hashBinary(char *strVal, int length);
    static unsigned int hashString(char *strVal);
    static void trimEnd(char *name)
    {
        while(*name!='\0')
        {
            if(*name == ' ') { *name='\0'; break;}
            name++;
        }
    }
    static void trimRight(char *name)
    {
        int len = strlen(name);
        while(name[len-1] == ' ' && len != 0 )
        {
             len--;
        }
        name[len]='\0';
    }
    static void str_tolower(char *s)
    {
        while(*s)
        {
           *s=tolower(*s);
           s++;
        }
    } 
    static void str_toupper(char *s)
    {
        while(*s)
        {
           *s=toupper(*s);
           s++;
        }
    } 
    static bool isIdentifier(char *name)
    {
        char *p = name;
        if (!isalpha(*p)) return false;
        while (*p != '\0') {
           if (*p == '_') { p++; continue; }
           if (!isalnum(*p)) return false;
           p++;
        }
        return true;
    }
    inline static void changeWildcardChar(char *src)
    {
        char *c = (char *)src;
        while (*c != '\0') {
            if (*c == '_') *c = '?';
            else if(*c == '%') *c = '*';
            c++;
        }
        return;
    }
    inline static void itoa(int n, char s[])
    {
       int i, sign, j, k ;
       if ((sign = n) < 0)  n = -n;          
       i = 0;
       do {       
          s[i++] = n % 10 + '0';   
       } while ((n /= 10) > 0);     
       if (sign < 0)
          s[i++] = '-';
       s[i] = '\0';
       char c;
       for (k = 0, j = i-1; k<j; k++, j--) {
          c = s[k];
          s[k] = s[j];
          s[j] = c;
       }
    } 
};

class ListNode
{
    public:
    void *element;
    ListNode *next;
    
};

class DllExport ListIterator
{
    ListNode *iter;
    ListNode *start;
    public:
    ListIterator(){}

    ListIterator(ListNode *head) { iter = head; start = head; }

    bool hasElement()
    {
        if (iter == NULL) return false; else return true;
    }

    void reset()
    {
        iter = start;
    }
    //isRemove ->the node needs to deleted after returning
    void* nextElement(bool isRemove = false) 
    {
        if (iter == NULL) return NULL;
        ListNode *node = iter;
        iter = iter ->next;
        return node->element;
    }
    void* nextElementInQueue() 
    {
        ListNode *node = iter;
        if(iter->next) {
            iter = iter ->next;
            return node->element;
        } else return NULL;
    }
    void *getCurrentListNode(){ return iter; }
    //index start with one, such that 1->first element in list
    void* getElement(int index)
    {
        ListNode *localIter = start;
        if (localIter == NULL) return NULL;
        for (int i=0; i <index; i++) {
           localIter = localIter->next;
           if (localIter == NULL) break;
        }
        return localIter->element;
    }
};

class Identifier
{
    public:
    char name[IDENTIFIER_LENGTH];
};

class DllExport List
{
    ListNode *head;
    int totalElements;
    public:
    List() { head = NULL; totalElements = 0;}
    List(ListNode *hd) { head = hd; } //Use only for free in metadata 
    DbRetVal append(void *elem)
    {
        ListNode *newNode = new ListNode();
        newNode->element = elem;
        newNode->next = NULL;
        totalElements++;
        //If this is the first node, set it as head
        if (NULL == head) { head = newNode; return OK; }

        ListNode *iter = head;
        while (NULL != iter->next) iter = iter->next;
        iter->next = newNode;
        return OK;
    }
    //Warning:Try to avoid using this method while using the iterator.The behavior 
    //is undefined. Instead set flag isRemove to yes and call nextElement of iterator.
    DbRetVal remove(void *elem, bool err=true) 
    {
        if (NULL == head)
        {
            if (err) 
               printError(ErrNotExists, "There are no elements in the list. Empty list");
            return ErrNotExists;
        }
        ListNode *iter = head, *prev = head;
        while (iter != NULL)
        {
            if (elem == iter->element)
            {
                if (iter == head) { 
                    head = iter->next; 
                    delete iter; 
                    totalElements--;
                    return OK;
                }
                prev->next = iter->next;
                delete iter;
                totalElements--;
                return OK;
            }
            prev = iter;
            iter = iter->next;
        }
        if (err) 
            printError(ErrNotFound, "There are no elements in the list");
        return ErrNotFound;
    }

    //index start with one, such that 1->first element in list
    void* get(int index)
    {
        ListNode *localIter = head;
        if (localIter == NULL) return NULL;
        for (int i=0; i <index -1; i++) {
           localIter = localIter->next;
           if (localIter == NULL) break;
        }
        return localIter->element;
    }


    bool exists(void *elem) 
    {
        ListNode *iter = head;
        while (iter != NULL)
        {
            if (elem == iter->element)
            {
                return true;
            }
            iter = iter->next;
        }
        return false;
    }

    ListIterator getIterator()
    {
        ListIterator iter(head);
        return iter;
    }
    void reset()
    {
        if (NULL == head) return;
        ListNode *iter = head, *prevIter = head;
        while (iter->next != NULL)
        {
            prevIter = iter;
            iter = iter->next;
            delete prevIter;

        }
        delete iter;
        head = NULL;
        totalElements = 0;
        return;
    }
    void init() { head = NULL; totalElements=0;}
    
    DbRetVal addAtMiddle(void *elem, void *prevIter)
    {
        ListNode *newNode = new ListNode();
        newNode->element = elem;
        totalElements++;
        newNode->next =((ListNode *)prevIter)->next;
        ((ListNode *)prevIter)->next = newNode;
        return OK;
    }
    DbRetVal addAtBegin(void *elem)
    {
        ListNode *newNode = new ListNode();
        newNode->element = elem;
        totalElements++;
        newNode->next = head;
        head = newNode;
        return OK;
    }
    int size()
    {
        return totalElements;
    }

};
#define MAX_UNIQUE_ID 10
class DllExport GlobalUniqueID
{
   void *ptr;
   public:
   GlobalUniqueID() { ptr = NULL; }
   DbRetVal create();
   DbRetVal open();
   DbRetVal close() { os::shm_detach(ptr); ptr = NULL; return OK; }
   DbRetVal destroy();
   int getID(UniqueIDType type);
};

class DllExport UniqueID
{
   int startID;
   Mutex mutex;
   public:
   UniqueID() { startID = 1; mutex.init("UID"); }


   void setID(int id)
   {
      startID = id;
      mutex.init("UID");
   }


   int getID()
   {
      //TODO::change mutex to atomic increment instruction
      if (mutex.getLock(-1, false) != 0) return 0;
      startID++;
      mutex.releaseLock(-1, false); 
      return startID;
   }
   void print()
   {
       printf("<UID value=%d>\n", startID);
       mutex.print();
       printf("</UID>\n");
   }
};

#endif
