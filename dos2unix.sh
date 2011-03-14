#/bin/sh 
for fileName in $(ls *.h); do 
cat $fileName | sed s///g >tmp && mv tmp $fileName 
done 
