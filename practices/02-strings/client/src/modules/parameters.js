const fs = require('fs');
const { showError } = require('./common');
require('colors');

const { kernelModulePath, parameters } = require('./kernel_module');

const readParameter = parameter => {
  const data = fs.readFileSync(parameter);
  data[data.length - 1] = '\0';

  return data;
};

const writeParameter = (parameter, str) => fs.writeFileSync(parameter, str);

const setParameter = (name, value) => {
  const parameter = parameters[name];

  try {
    if (!parameter) {
      throw `This parameter: ${name} doesn't exists.`;
    }

    writeParameter(`${kernelModulePath}${parameter.name}`, value);
  } catch (err) {
    showError(err);
  }
};

const showAllParameters = () =>
  Object.keys(parameters).forEach(name => {
    showParameter(name);
    console.log();
  });

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

const valStr = str => /^[\x00-\x7F]*$/.test(str) || 'Only ASCII characters';

const valLetter = str =>
  /^[\x00-\x7F]$/.test(str) || 'Only one ASCII character';

module.exports = {
  valStr,
  valLetter,
  setParameter,
  showParameter,
  showAllParameters,
};
