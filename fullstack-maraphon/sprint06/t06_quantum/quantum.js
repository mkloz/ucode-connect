function calculateTime() {
  const startDate = new Date('1939-01-01');
  const currentDate = new Date();

  const totalDays = Math.floor(
    (currentDate - startDate) / (1000 * 60 * 60 * 24),
  );
  const quantumYears = Math.floor(totalDays / (7 * 365));
  const quantumMonths = Math.floor((totalDays % (7 * 365)) / (7 * 30));
  const quantumDays = Math.floor((totalDays % (7 * 365)) % (7 * 30));

  return [quantumYears, quantumMonths, quantumDays];
}

module.exports = {
  calculateTime,
};
