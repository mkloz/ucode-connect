function firstUpper(string) {
  if (!string) return string;

  if (string == '' || string == null) return '';
  string = string.trim().toLowerCase();
  string = string.charAt(0).toUpperCase() + string.slice(1, string.length);

  return string;
}

module.exports.firstUpper = firstUpper;
