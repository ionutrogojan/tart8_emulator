"use.strict";

const canvas_element = document.querySelector("canvas");
const ctx = canvas_element.getContext("2d");

const canvas_settings = {
	width: 192,
	height: 144,
	scale: 4,
	tile: 8,
}

const cursor_pos = {
	x: 0,
	y: 0
}

init(canvas_settings.width, canvas_settings.height, canvas_settings.scale);

function init(width, height, scale) {
	canvas_element.setAttribute("width", width);
	canvas_element.setAttribute("height", height);
	canvas_element.style.setProperty("--canvas-scale", scale);
}

let layer = new Uint8ClampedArray(canvas_settings.width * canvas_settings.height * 4).fill(0);

document.addEventListener("keyup", (e) => {
	// console.log(e.key);
	switch (e.key) {
		case "ArrowLeft":
			if (cursor_pos.x <= 0) return
			else { cursor_pos.x -= canvas_settings.tile }
			break;
		case "ArrowRight":
			if (cursor_pos.x >= canvas_settings.width - canvas_settings.tile) return
			else { cursor_pos.x += canvas_settings.tile }
			break;
		case "ArrowUp":
			if (cursor_pos.y <= 0) return
			else { cursor_pos.y -= canvas_settings.tile }
			break;
		case "ArrowDown":
			if (cursor_pos.y >= canvas_settings.height - canvas_settings.tile) return
			else { cursor_pos.y += canvas_settings.tile }
			break;
		default:
			// do nothing
			break;
	}
	draw_tile(cursor_pos.x, cursor_pos.y)
}, false);

function draw_tile(pos_x, pos_y) {
	console.log(pos_x / 8, pos_y / 8);
	
	for (let o = 0; o < canvas_settings.tile; o++) {
		const pos = (pos_x * 4) + ((pos_y + o) * canvas_settings.width * 4);
		draw_tile_horizontal(canvas_settings.tile * 4, 4, pos, { R: 153, G: 46, B: 153, A: 255 });
	}

	const layer_data = new ImageData(layer, canvas_settings.width, canvas_settings.height);
	ctx.putImageData(layer_data, 0, 0);
}

function draw_tile_horizontal(max, step, pos, { R, G, B, A }) {
	for (let i = 0; i < max; i += step) {
		layer[pos + i + 0] = R;
		layer[pos + i + 1] = G;
		layer[pos + i + 2] = B;
		layer[pos + i + 3] = A;
	}
}