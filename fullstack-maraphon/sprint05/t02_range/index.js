function checkDivision(start = 60, end = 60) {
  for (let num = start; num <= end; num++) {
    var msg = ' - ';

    if (num % 2 === 0) msg = ' is divisible by 2';
    if (num % 3 === 0 && num % 2 !== 0) msg = ' is divisible by 3';
    else if (num % 3 === 0) msg = msg.concat(', is divisible by 3');
    if (num % 10 === 0) msg = msg.concat(', is divisible by 10');
    console.log('The number ' + num + msg + '');
  }
}

module.exports.checkDivision = checkDivision;
