const apiKey = 'Your API Key';
const city = 'New York';

async function getWeatherData() {
    const response = await fetch(
        `https://api.openweathermap.org/data/3.0/forecast?q=${city}&units=metric&appid=${apiKey}`,
    );
    const data = await response.json();
    displayWeatherData(data);
}

function displayWeatherData(data) {
    const weatherContainer = document.getElementById('weather-container');
    weatherContainer.innerHTML = '';

    const forecastList = data.list.filter((item) =>
        item.dt_txt.includes('12:00:00'),
    );

    forecastList.forEach((forecast) => {
        const date = new Date(forecast.dt * 1000);
        const options = { weekday: 'long', month: 'long', day: 'numeric' };
        const dateString = date.toLocaleDateString('en-US', options);

        const temperature = Math.round(forecast.main.temp);
        const weatherDescription = forecast.weather[0].description;
        const weatherIcon = `http://openweathermap.org/img/wn/${forecast.weather[0].icon}.png`;

        const weatherCard = document.createElement('div');
        weatherCard.className = 'weather-card';
        weatherCard.innerHTML = `
            <h3>${dateString}</h3>
            <img src="${weatherIcon}" alt="${weatherDescription}">
            <p>${weatherDescription}</p>
            <p>${temperature} °C</p>
        `;
        weatherContainer.appendChild(weatherCard);
    });
}

getWeatherData();
