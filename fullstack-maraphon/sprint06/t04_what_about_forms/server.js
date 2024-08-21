const http = require('http');
const fs = require('fs');
const url = require('url');
const querystring = require('querystring');

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  const parsedUrl = url.parse(req.url);

  if (parsedUrl.pathname === '/' && req.method === 'GET') {
    fs.readFile('index.html', (err, data) => {
      if (err) {
        res.writeHead(500, { 'Content-Type': 'text/plain' });
        res.end('Internal Server Error');
        return;
      }
      res.writeHead(200, { 'Content-Type': 'text/html' });
      res.end(data);
    });
  } else if (parsedUrl.pathname === '/submit' && req.method === 'POST') {
    let body = '';
    req.on('data', (chunk) => {
      body += chunk.toString();
    });
    req.on('end', () => {
      const parsedBody = querystring.parse(body);
      const answer = parsedBody.answer;
      let message;
      if (answer === 'correct') {
        message = 'Correct! Iron Man is Tony Stark.';
      } else {
        message = 'Incorrect! Try again.';
      }
      res.writeHead(200, { 'Content-Type': 'text/html' });
      res.end(`<h1>${message}</h1><a href="/">Go back</a>`);
    });
  } else {
    res.writeHead(404, { 'Content-Type': 'text/plain' });
    res.end('Not Found');
  }
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});
