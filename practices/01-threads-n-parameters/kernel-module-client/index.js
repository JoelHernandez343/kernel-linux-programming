const app = require('./src/app');

app();

// const fs = require('fs');

// const parameter = '/sys/module/param_3/parameters/comando';

// const readParameter = parameter => {
//   const data = fs.readFileSync(parameter);
//   data[data.length - 1] = '\0';

//   return data;
// };

// const writeParameter = (parameter, str) => {
//   fs.writeFileSync(parameter, str);
// };

// // writeParameter(parameter, 'izquierda');

// try {
//   const data = readParameter(parameter);
//   console.log(data.toString('utf8'));
// } catch (err) {
//   console.log(err);
// }
