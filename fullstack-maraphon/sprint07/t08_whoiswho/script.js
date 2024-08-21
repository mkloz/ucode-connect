document
  .getElementById('upload-form')
  .addEventListener('submit', async (event) => {
    event.preventDefault();
    const formData = new FormData(event.target);
    const response = await fetch('/upload', {
      method: 'POST',
      body: formData,
    });
    const data = await response.json();
    populateTable(data);
    populateFilterOptions(data);
  });

document
  .getElementById('filter-form')
  .addEventListener('submit', async (event) => {
    event.preventDefault();
    const column = document.getElementById('column').value;
    const filter = document.getElementById('filter').value;
    const response = await fetch(`/filter?column=${column}&filter=${filter}`);
    const data = await response.json();
    populateTable(data);
  });

function populateTable(data) {
  const tableHead = document.getElementById('table-head');
  const tableBody = document.getElementById('table-body');

  tableHead.innerHTML = '';
  tableBody.innerHTML = '';

  if (data.length > 0) {
    const columns = Object.keys(data[0]);
    const headerRow = document.createElement('tr');
    columns.forEach((column) => {
      const th = document.createElement('th');
      th.textContent = column;
      headerRow.appendChild(th);
    });
    tableHead.appendChild(headerRow);

    data.forEach((row) => {
      const tr = document.createElement('tr');
      columns.forEach((column) => {
        const td = document.createElement('td');
        td.textContent = row[column];
        tr.appendChild(td);
      });
      tableBody.appendChild(tr);
    });
  }
}

function populateFilterOptions(data) {
  const columnSelect = document.getElementById('column');
  columnSelect.innerHTML = '';

  if (data.length > 0) {
    const columns = Object.keys(data[0]);
    columns.forEach((column) => {
      const option = document.createElement('option');
      option.value = column;
      option.textContent = column;
      columnSelect.appendChild(option);
    });
  }
}
