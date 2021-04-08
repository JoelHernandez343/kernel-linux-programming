const kernelModulePath = '/sys/module/kpractice01/parameters/';

const parameters = {
  average: {
    value: 'average',
    access: 'r',
  },
  data: {
    value: 'data',
    access: 'rw',
  },
  evenData: {
    value: 'even_data',
    access: 'r',
  },
  option: {
    value: 'option',
    access: 'rw',
  },
};

module.exports = {
  kernelModulePath,
  parameters,
};
