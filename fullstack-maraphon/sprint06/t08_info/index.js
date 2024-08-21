const http = require('http');
const path = require('path');
const os = require('os');

const server = http.createServer((req, res) => {
  // 1. Name of the executed script
  const filename = path.basename(__filename);
  console.log('Name of the executed script: ' + filename);

  // 2. Arguments passed to the script
  console.log('Arguments passed to the script:');
  process.argv.forEach((val, index) => {
    console.log(`${index}: ${val}`);
  });

  // 3. IP address of the server
  const ip = req.headers['x-forwarded-for'] || req.connection.remoteAddress;
  console.log('IP address of the server: ' + ip);

  // 4. Name of host that invokes the current script
  const hostname = os.hostname();
  console.log('Name of host that invokes the current script: ' + hostname);

  // 5. Protocol used by the request
  console.log('Protocol: ' + req.protocol);

  // 6. All request headers
  console.log('Request headers:');
  console.log(req.headers);

  // 7. User agent
  console.log('User agent: ' + req.headers['user-agent']);

  // 8. IP address of the client
  console.log('IP address of the client: ' + req.connection.remoteAddress);

  // 9. All request headers as JSON string
  console.log('All request headers as JSON string:');
  console.log(JSON.stringify(req.headers, null, 2));

  res.end('');
});

const port = 3000;
const host = '127.0.0.1';

server.listen(port, host, () => {
  console.log(`Server is running at http://${host}:${port}`);
});
