# cd-bookmark
A little program that performs cd command with bookmark feature, also a practice of autotools for myself.

#Installation
Clone the repo then do a configure-make-install procedure:
``` bash
$ git clone https://github.com/austin880625/cd-bookmark.git
$ cd cd-bookmark
$ ./configure
$ make
$ sudo make install
```

#Usage
First add a `.bookmark` file under home directory in the following format:
```
entry-name1	/the/actual/path1
entry-name2	/the/actual/path2
```
The entry names and the actual paths are seperated by tab characters

Then change the working directory by `. cdd entry-name1` command
