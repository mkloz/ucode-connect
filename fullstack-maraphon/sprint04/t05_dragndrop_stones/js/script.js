const state = {
    target: null,
    offsetX: 0,
    offsetY: 0,
};

const area = document.getElementById('area');

function handleMouseDown(event) {
    if (
        event.target.classList.contains('stone') &&
        event.target.getAttribute('value') === 'on'
    ) {
        event.target.style.cursor = 'none';
        state.target = event.target;
        state.offsetX = event.offsetX;
        state.offsetY = event.offsetY;
    }
}

function handleMouseUp(event) {
    if (state.target) {
        state.target.style.cursor = 'default';
        state.target = null;
    }
}

function handleMouseMove(event) {
    if (state.target) {
        state.target.style.position = 'absolute';
        state.target.style.left = `${event.pageX - state.offsetX}px`;
        state.target.style.top = `${event.pageY - state.offsetY}px`;
    }
}

function handleDoubleClick(event) {
    if (event.target.classList.contains('stone')) {
        const currentValue = event.target.getAttribute('value');
        event.target.setAttribute(
            'value',
            currentValue === 'on' ? 'off' : 'on',
        );
    }
}

area.addEventListener('mousedown', handleMouseDown);
document.addEventListener('mouseup', handleMouseUp);
document.addEventListener('mousemove', handleMouseMove);
area.addEventListener('dblclick', handleDoubleClick);
