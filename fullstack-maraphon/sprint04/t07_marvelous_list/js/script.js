function showFilmInfo(id) {
    const filmInfos = document.querySelectorAll('.film-info');
    filmInfos.forEach((info) => {
        if (info.id === id) {
            info.classList.add('active');
        } else {
            info.classList.remove('active');
        }
    });
}
