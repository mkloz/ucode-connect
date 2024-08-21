let slideIndex = 1;
const slides = document.getElementsByClassName('slide');
let timeId;

function showSlides(n) {
    slideIndex = n > slides.length ? 1 : n < 1 ? slides.length : n;

    Array.from(slides).forEach((slide) => (slide.style.display = 'none'));
    slides[slideIndex - 1].style.display = 'block';

    clearInterval(timeId);
    timeId = setInterval(() => showSlides((slideIndex += 1)), 3000);
}

function nextSlide() {
    showSlides(++slideIndex);
}
function prevSlide() {
    showSlides(--slideIndex);
}

showSlides(slideIndex);
