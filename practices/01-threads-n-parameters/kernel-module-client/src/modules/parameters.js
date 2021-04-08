const fs = require('fs');

const readParameter = parameter => {
  const data = fs.readFileSync(parameter);
  data[data.length - 1] = '\0';

  return data;
};

const writeParameter = (parameter, str) => {
  fs.writeFileSync(parameter, str);
};

module.exports = { readParameter, writeParameter };
