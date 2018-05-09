# Install FFTW
```sh
cd
mkdir fftw3
cd fftw3
wget http://www.fftw.org/fftw-3.3.5.tar.gz
tar xvzf fftw-3.3.5.tar.gz
cd fftw-3.3.5/
./configure --prefix=$HOME/fftw3 --enable-float --enable-sse2
make
make install
```
