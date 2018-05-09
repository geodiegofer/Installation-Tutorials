# Installing Madagascar

We followed http://www.ahay.org/wiki/Installation#Troubleshooting. Steps:

1. Install the most recent anaconda version (python 3).

2. Set a python 2 environment:
`conda create --name py2 python=2`

3. Instale o Python 2.x.x. I followed [this](https://help.dreamhost.com/hc/en-us/articles/115000218612-Installing-a-custom-version-of-Python-2).

4. Set `PYTHONPATH` variable.
`export PATH=$HOME/opt/python-2.7.7/bin:$PATH`

5. On terminal,
```sh
cd
mkdir madagascar2.0
cd madagascar2.0
```
6. Following the instructions [here](http://www.ahay.org/wiki/Download), download and unzip the file at the folder ~/madagascar2.0.

6. Edit the end of ~/.bashrc (i.e. `gedit ~/.bashrc`):
```sh
# Madagascar exports
export RSFROOT=~/madagascar-2.0 # 
if [ -n "$PYTHONPATH" ]; then
export PYTHONPATH=${PYTHONPATH}:$RSFROOT/lib
else
export PYTHONPATH=$RSFROOT/lib
fi
export PATH=$RSFROOT/bin:$PATH
export DATAPATH=/var/tmp/
export MANPATH=$RSFROOT/share/man:$(manpath)
export LD_LIBRARY_PATH=$RSFROOT/lib:$LD_LIBRARY_PATH
source $RSFROOT/env.sh
export DATAPATH=$RSFROOT/DATA/
```

7. On terminal,
```sh
bash
source activate python2
cd
cd madagascar2.0
./configure --prefix=.
./configure API=c++,f90 --prefix=.
make
make install
```
8. Cross your fingers.

9. If successful, run the tests on http://www.ahay.org/wiki/Installation#Troubleshooting to see if it is working. If not, go read this same link to troubleshoot (good luck).

10. Always run `source activate py2` before using Madagascar. This is a python 2 environment, required by Madagascar. 
When you are done, type `source deactivate`. 
