let date = new Date('01-01-1939');

function calculateTime() {
  let now = new Date();

  return {
    years() {
      return now.getFullYear() - date.getFullYear() - 1;
    },
    months() {
      return now.getMonth() - date.getMonth() - 1;
    },
    days() {
      return now.getDate() - date.getDate() - 4;
    },
  };
}

module.exports = function normalRouter(req, res) {
  const time = calculateTime();
  const html = `
        <html>
        <head><title>Normal Space Time</title></head>
        <body>
            <h1>Normal Space Time</h1>
            <p>In real life, you were absent for ${time.years()} years, ${time.months()} months, and ${time.days()} days.</p>
        </body>
        </html>
    `;
  res.writeHead(200, { 'Content-Type': 'text/html' });
  res.end(html);
};
