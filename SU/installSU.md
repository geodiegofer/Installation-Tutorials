# STEPS TO INSTALL SEISMIC UNIX AND NIMAGE
(Based on SU's git https://github.com/JohnWStockwellJr/SeisUnix/wiki/Seismic-Unix-install-on-Ubuntu )
```sh
cd
mkdir -p ~/cwp/43R1
cd ~/cwp/43R1
wget ftp://ftp.cwp.mines.edu/pub/cwpcodes/cwp_su_all_43R1.tgz
tar -zxvf cwp_su_all_43R1.tgz

echo "export CWPROOT=~/cwp/43R1" >> ~/.bashrc
echo "export PATH=$PATH:~/cwp/43R1/bin" >> ~/.bashrc
source ~/.bashrc

cd $CWPROOT/src
sudo apt-get install build-essential
make install
sudo apt-get install libx11-dev
sudo apt-get install libxt-dev
make xtinstall
```

# (OPTIONAL) Install nimage
Copy nimage.c to ~/cwp/43R1/src/xplot/main
Edit Makefile on ~/cwp/43R1/src/xplot/main, changing
```makefile
PROGS =			\
	$B/lcmap	\
	$B/lprop	\
	$B/scmap	\
	$B/xcontour	\
	$B/ximage	\
	$B/xwigb	\
	$B/xpicker	
```

to (USE TAB FOR SPACING)

```Cmake
PROGS =			\
	$B/lcmap	\
	$B/lprop	\
	$B/scmap	\
	$B/xcontour	\
	$B/ximage	\
	$B/xwigb	\
	$B/xpicker	\
    $B/nimage   
```

```sh
cd ~/cwp/43R1/src 
make xtinstall
```

# After installing: problems when sourcing SU libraries in your program
1. Problems with compiler finding and linking things may arise. Read this tutorial: https://homepages.inf.ed.ac.uk/imurray2/compnotes/library_linking.txt .

2. When compiling the compiler might not find `Complex.h`. Copying `Complex.h` (from wherever it is - use `find`) to ~/43R1/include may solve the problem.

3. You might need to export a bunch of stuff, if the system does not read your includes (solutions if any of the problems in 1 appear; read the tutorial for a detailed explanation):
```sh
# Finding stuff you need inside package folder
find /home/username/ -name "*.err"
find ~/victor-ROG2018/43R1 -name "Complex"

# Exports for the compiling step
echo "export CPATH=$CPATH:~/victor-ROG2018/43R1/:~/victor-ROG2018/43R1/bin:~/victor-ROG2018/43R1/include" >> ~/.bashrc
echo "export CPATH=$CPATH:~/victor-ROG2018/43R1/src/:~/victor-ROG2018/43R1/src/Complex/include/" >> ~/.bashrc
bash

# Exports for the linking step
echo "export LIBRARY_PATH=$LIBRARY_PATH:~/victor-ROG2018/43R1/:~/victor-ROG2018/43R1/bin:~/victor-ROG2018/43R1/include" >> ~/.bashrc
echo "export LIBRARY_PATH=$LIBRARY_PATH:~/victor-ROG2018/43R1/src/:~/victor-ROG2018/43R1/src/Complex/include/" >> ~/.bashrc 
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/victor-ROG2018/43R1/src/:~/victor-ROG2018/43R1/src/Complex/include/" >> ~/.bashrc
bash

# Export for the linking step (CUDA libraries)
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64" >> ~/.bashrc
bash
```
The last export is not related to SU, but to using CUDA.
