const fs = require('fs');
const { showError } = require('./common');
require('colors');

const { kernelModulePath, parameters } = require('./kernel_module');

const readParameter = parameter => {
  const data = fs.readFileSync(parameter);
  data[data.length - 1] = '\0';

  return data;
};

const writeParameter = (parameter, str) => {
  fs.writeFileSync(parameter, str);
};

const showParameter = name => {
  const parameter = parameters[name];

  try {
    if (!parameter) {
      throw `This parameter: ${name} doesn't exists.`;
    }

    const value = readParameter(`${kernelModulePath}${parameter.name}`);

    console.log(`  ${'Parameter: '.yellow.bold}   ${parameter.name}`);
    console.log(`  ${'Permission: '.yellow.bold}  ${parameter.access}`);
    console.log(`  ${'Value: '.yellow.bold}       ${value}`);
  } catch (err) {
    showError(err);
  }
};

module.exports = { readParameter, writeParameter, showParameter };
