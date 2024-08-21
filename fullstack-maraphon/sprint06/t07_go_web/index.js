const http = require('http');
const normalRouter = require('./normal-router');
const quantumRouter = require('./quantum-router');

const host = 'localhost';
const port = 3000;

const server = http.createServer((req, res) => {
  if (req.url === '/') {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('Welcome to the Time Space Router');
  } else if (req.url === '/normal') {
    normalRouter(req, res);
  } else if (req.url === '/quantum') {
    quantumRouter(req, res);
  } else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.end('404 - Not Found');
  }
});

server.listen(port, host, () => {
  console.log(`Server running at http://${host}:${port}/`);
});
