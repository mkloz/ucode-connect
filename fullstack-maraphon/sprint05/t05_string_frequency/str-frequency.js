module.exports = class StrFrequency {
  constructor(str) {
    this.str = str;
  }
  letterFrequencies() {
    return this.str.split('').reduce((arr_print, x) => {
      x = x.toUpperCase();
      if (!x.match(/[A-Z]/)) return arr_print;
      if (arr_print.hasOwnProperty(x)) arr_print[x] += 1;
      else arr_print[x] = 1;
      return arr_print;
    }, {});
  }
  wordFrequencies() {
    if (this.str == '') return { '': 1 };

    return this.str.split(/\b/).reduce((arr_print, x) => {
      x = x.toUpperCase();
      if (!x.match(/[A-Z]/)) return arr_print;
      if (arr_print.hasOwnProperty(x)) arr_print[x] += 1;
      else arr_print[x] = 1;

      return arr_print;
    }, {});
  }
  reverseString() {
    return this.str.split('').reverse().join('');
  }
};
