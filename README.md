# Discrete Time Event Simulation

![GitHub Actions](https://github.com/otaviofbrito/discrete-time-event-simulation/actions/workflows/makefile.yml/badge.svg)

:chart_with_upwards_trend: An example report is available on [Github Pages](https://otaviofbrito.github.io/discrete-time-event-simulation/report.html).


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
```

After the build process, you can run the project:

```shell
# Run project
make
```

Once executed, a report will automatically open, displaying the graphical visualizations:

```shell
# Clean objects, reports and generated data
make clean
```

You can also run it with predefined inputs in the inputs.txt file:
```shell
# Express run with inputs.txt
make auto
```

To fully clean the environment, run:
```shell
# Remove generated data, objects and virtual environment
make purge
```
