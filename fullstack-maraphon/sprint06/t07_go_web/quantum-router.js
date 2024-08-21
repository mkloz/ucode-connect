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

module.exports = function quantumRouter(req, res) {
  const quantumTime = calculateTime();
  const html = `
        <html>
        <head><title>Quantum Space Time</title></head>
        <body>
            <h1>Quantum Space Time</h1>
            <p>In quantum space, you were absent for ${quantumTime[0]} years, ${quantumTime[1]} months, and ${quantumTime[2]} days.</p>
        </body>
        </html>
    `;
  res.writeHead(200, { 'Content-Type': 'text/html' });
  res.end(html);
};
