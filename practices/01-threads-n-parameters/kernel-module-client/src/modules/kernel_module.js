const kernelModulePath = '/sys/module/kpractice01/parameters/';

const parameters = {
  average: {
    name: 'average',
    access: 'r',
  },
  data: {
    name: 'data',
    access: 'rw',
  },
  evenData: {
    name: 'even_data',
    access: 'r',
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
