
mkdir -p inputFiles

if test -f doneFiles/CDRFile1.cdr
then
	mv doneFiles/CDRFile0.cdr inputFiles
	mv doneFiles/CDRFile1.cdr inputFiles
else
	echo "files don't exist. creating files"
	cd fileGenerator 
	gcc -o generator.out CDR_genrator.c 
	./generator.out 
	mv CDRFile0.cdr CDRFile1.cdr ../inputFiles
fi

