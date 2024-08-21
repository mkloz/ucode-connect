window.onload = function() {
    fetch('/toXML')
        .then(response => response.json())
        .then(data => {
            document.querySelector('#to').innerText = data.to;
            document.querySelector('#from').innerText = data.from;
            render('#to', data);
            console.log(data);
        });
};