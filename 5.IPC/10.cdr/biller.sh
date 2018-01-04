mkdir -p log
mkdir -p invalidFiles
mkdir -p inputFiles
mkdir -p doneFiles

make

rm log/Controller.log
rm log/feeder.log
rm log/processor.log

export LD_LIBRARY_PATH=../../../lib:$LD_LIBRARY_PATH

cd CDRprocessor
./CdrProcessor.out&

cd ../feeder
./feeder.out&

cd ../UI
./controllerMain.out
