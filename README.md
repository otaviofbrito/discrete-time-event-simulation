# Discrete Time Event Simulation

### Pre-Requisites
These tools are often pre-installed on your OS. If not, visit their websites and install them:
- [Python 3](https://www.python.org/downloads/source/)
- [pip](https://pypi.org/project/pip/)
- [GCC](https://gcc.gnu.org/install/)
- [GNU Make](https://www.gnu.org/software/make/)

### Usage
The project can be easily built using a Makefile.

At the root directory, run the following commands:
```shell
# Build project and install dependencies
make build

# Next, activate the python environment
source .env/bin/activate
```

After the build process, you can run the project:

```shell
# Run project
make
```

Once executed, a report will automatically open, displaying the graphical visualizations.

```shell
# Clean objects, reports and generated data
make clean
```
---