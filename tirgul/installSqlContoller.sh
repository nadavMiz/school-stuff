sudo apt-get install cmake
sudo apt-get install libmysqlcppconn-dev
git clone https://github.com/mysql/mysql-connector-cpp.git
cd mysql-connector-cpp
cmake .
make clean
make
sudo make install
cd ../
rm -rf mysql-connector-cpp
echo -e '\033[0;36minstallation done!. thank you for using nadav installer :)'

