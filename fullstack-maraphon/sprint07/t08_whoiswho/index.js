const express = require('express');
const multer = require('multer');
const csv = require('csv-parser');
const fs = require('fs');

const app = express();
const upload = multer({ dest: 'uploads/' });
const PORT = 3000;

app.use(express.static(__dirname));
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

let csvData = [];

app.post('/upload', upload.single('file'), (req, res) => {
  const filePath = req.file.path;

  csvData = [];
  fs.createReadStream(filePath)
    .pipe(csv())
    .on('data', (row) => {
      csvData.push(row);
    })
    .on('end', () => {
      fs.unlinkSync(filePath);
      res.json(csvData);
    });
});

app.get('/filter', (req, res) => {
  const filter = req.query.filter;
  const column = req.query.column;
  let filteredData = csvData;

  if (filter && column) {
    filteredData = csvData.filter((row) => row[column] === filter);
  }

  res.json(filteredData);
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
