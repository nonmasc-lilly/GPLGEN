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
- `--help` | `-h` shows a help menu
- `--config <config>` | `-c <config>` creates a config file `(<config>)` of the current project name copyyear author
                                      and description
- `--useconfig <config>` | `-u <config>` uses the options in config file `(<config>)`
- `--dontwrite` dont write the comment to a file (useful for generating a config file without also generating a new
                file

you may install GPLGEN by cd-ing into the main directory and running

```
sudo make INSTALL
```
