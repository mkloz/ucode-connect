const express = require('express');
const cookieParser = require('cookie-parser');
const path = require('path');

const app = express();
const PORT = 3000;

app.use(cookieParser());
app.use(express.static(__dirname));
app.get('/count', (req, res) => {
  let pageLoads = JSON.parse(req.cookies.pageLoads || '[]');
  const now = Date.now();
  const oneMinuteAgo = now - 60000;

  pageLoads = pageLoads.filter((timestamp) => timestamp > oneMinuteAgo);
  pageLoads.push(now);
  res.cookie('pageLoads', JSON.stringify(pageLoads), { maxAge: 60000 });
  res.json({ count: pageLoads.length });
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
