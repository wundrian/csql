#include<Util.h>
#include<Config.h>

DbRetVal GlobalUniqueID::create()
{
    int key = Conf::config.getShmIDKey();
    int id = os::shm_create(key, MAX_UNIQUE_ID *sizeof(int), 0666);
    if (-1 == id) {
	    printError(ErrOS, "Unable to create shared memory");
	    return ErrOS;
    }
    ptr = os::shm_attach(id, NULL, 0);
    if ((void*)-1 == ptr) {
        printError(ErrOS, "Unable to attach shared memory");
	    return ErrOS;
    }
    memset(ptr, 0, MAX_UNIQUE_ID *sizeof(int));
}
   
DbRetVal GlobalUniqueID::open() 
{
    int key = Conf::config.getShmIDKey();
    int id = os::shm_open(key, MAX_UNIQUE_ID *sizeof(int), 0666);
    if (-1 == id) {
        printError(ErrOS, "Unable to create shared memory");
    }
    ptr = os::shm_attach(id, NULL, 0);
    if ((void*)-1 == ptr) {
        printError(ErrOS, "Unable to create shared memory");
    }
    return OK;
}

DbRetVal GlobalUniqueID::destroy()
{
    int key = Conf::config.getShmIDKey();
    int id = os::shm_open(key, MAX_UNIQUE_ID *sizeof(int), 0666);
    if (-1 == id) {
        printError(ErrOS, "Unable to open shared memory");
        return ErrOS;
    }
    os::shmctl(id, IPC_RMID);
}

int GlobalUniqueID::getID(UniqueIDType type)
{
    int *id = (int*)(((char*)ptr) + sizeof(int) * type);
    int oldVal = *id;
    int ret = Mutex::CAS(id, oldVal, oldVal+1);
    if (ret) return -1;
    return *id;
}

