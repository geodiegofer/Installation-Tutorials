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
make install
sudo apt-get install libx11-dev
sudo apt-get install libxt-dev
make xtinstall
```

Alter makefile to make CWPROOT variable equal to the place installed
Example:
CWPROOT = /home/linton/cwp/43R1

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

# Possible problems
When compiling the compiler might not find `Complex.h`. Copying `Complex.h` (from wherever it is - use `find`) to ~/43R1/include may solve the problem.
