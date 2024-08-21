function isInViewport(element) {
    const rect = element.getBoundingClientRect();
    return (
        rect.top >= 0 &&
        rect.left >= 0 &&
        rect.bottom <=
            (window.innerHeight || document.documentElement.clientHeight) &&
        rect.right <=
            (window.innerWidth || document.documentElement.clientWidth)
    );
}

function lazyLoadImages() {
    const images = document.querySelectorAll('.image img');
    let loadedCount = 0;

    images.forEach((image) => {
        if (isInViewport(image)) {
            const src = image.getAttribute('data-src');
            if (src && image.src !== src) {
                image.src = src;
                image.onload = () => {
                    loadedCount++;
                    updateMessage(loadedCount);
                };
            }
        }
    });
}

function updateMessage(count) {
    const message = document.getElementById('message');
    message.innerText = `Loaded ${count} images.`;
}

lazyLoadImages();
window.addEventListener('scroll', lazyLoadImages);
