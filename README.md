# GPLGEN

GPLGEN is a simple program to generate GNU General Public
Licence files and headers. It is to be used to streamline
the process of marking files with GPL comments and to add
a LICENCE file to your project.


It is ran as follows:

```
gplgen [*OPTIONS] filename
```

with the following possible options:

- `--licence` | `-l`: places the oficial GNU GPL licence file into `filename`
- `--project <name>` | `-p <name>`: sets the name of the project
- `--copyyear <year>` | `-y <year>`: set the year of copyright
- `--author <name>` | `-a <name>`: sets the author name
- `--desc <description>` | `-d <description>` sets the program description
- `--subname` | `-s` appends `(<filename>)` to the end of the description

you may install GPLGEN by cd-ing into the main directory and running

```
sudo make INSTALL
```
