const kernelModulePath = '/sys/module/kpractice02/parameters/';

const parameters = {
  coincidences: {
    name: 'coincidences',
    access: 'r',
  },
  length: {
    name: 'length',
    access: 'rw',
  },
  str: {
    name: 'str',
    access: 'rw',
  },
  letter: {
    name: 'letter',
    access: 'rw',
  },
  option: {
    name: 'option',
    access: 'rw',
  },
};

module.exports = {
  kernelModulePath,
  parameters,
};
