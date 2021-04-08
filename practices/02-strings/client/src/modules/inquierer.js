require('colors');

const inquirer = require('inquirer');
// const { validateArray, transformArray } = require('./parameters');

const questions = prev => ({
  type: 'list',
  name: 'option',
  message: 'Select an option',
  loop: false,
  default: prev,
  choices: [
    {
      value: '1',
      name: `${'1.'.green.bold} Show all parameters`,
    },
    {
      value: 'option',
      name: `${'2.'.green.bold} Show <${'option'.red.bold}> parameter`,
    },
    {
      value: 'str',
      name: `${'3.'.green.bold} Show <${'str'.red.bold}> parameter`,
    },
    {
      value: 'letter',
      name: `${'4.'.green.bold} Show <${'letter'.red.bold}> parameter`,
    },
    {
      value: 'coincidences',
      name: `${'5.'.green.bold} Show <${'coincidences'.red.bold}> parameter`,
    },
    {
      value: 'length',
      name: `${'8.'.green.bold} Show <${'length'.red.bold}> parameter`,
    },
    {
      value: '7',
      name: `${'7.'.green.bold} Set string`,
    },
    {
      value: '8',
      name: `${'8.'.green.bold} Set letter to compare with`,
    },
    {
      value: '9',
      name: `${'9.'.green.bold} Invoke method of kernel module`,
    },
    new inquirer.Separator('------------------------------------'),
    {
      value: '10',
      name: `${'10.'.green.bold} About`,
    },
    {
      value: '0',
      name: `${'11.'.green.bold} Exit`,
    },
    new inquirer.Separator('------------------------------------'),
  ],
});

const menu = async prev => {
  console.clear();
  console.log('--------------------------------------'.yellow.bgBlack);
  console.log('          Kernel module app           '.white.bgBlack.bold);
  console.log('--------------------------------------\n'.yellow.bgBlack);

  const { option } = await inquirer.prompt(questions(prev));

  return option;
};

const pause = async () =>
  await inquirer.prompt({
    name: '_',
    message: `Press ${'ENTER'.green} to continue.`,
  });

// const askArray = async () => {
//   const { array } = await inquirer.prompt({
//     name: 'array',
//     message: `Input the array's values separated by ",". Limit 8:`,
//     validate: validateArray,
//   });

//   return transformArray(array);
// };

// const askOption = async () => {
//   const { option } = await inquirer.prompt({
//     type: 'list',
//     name: 'option',
//     message: `Select module's method to invoke:`,
//     choices: [
//       {
//         value: 1,
//         name: `${'1.'.green.bold} Calculate average`,
//       },
//       {
//         value: 2,
//         name: `${'2.'.green.bold} Sort array`,
//       },
//       {
//         value: 3,
//         name: `${'3.'.green.bold} Find even numbers`,
//       },
//       {
//         value: 0,
//         name: `${'4.'.green.bold} Cancel`,
//       },
//     ],
//   });

//   return option;
// };

module.exports = {
  menu,
  pause,
};
