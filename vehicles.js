const NUM_VEHICLES = 5;

const FIELDS = [
  { key: "id", label: "Vehicle ID", type: "text" },
  { key: "type", label: "Type", type: "text" },
  { key: "price", label: "Price", type: "text" },
];

function buildForm(container) {
  for (let i = 0; i < NUM_VEHICLES; i++) {
    const row = document.createElement("fieldset");
    row.className = "vehicle-row";

    FIELDS.forEach((field) => {
      const wrapper = document.createElement("div");
      wrapper.className = "field";

      const input = document.createElement("input");
      input.type = field.type;
      input.id = `${field.key}-${i}`;
      input.name = `${field.key}-${i}`;
      input.dataset.field = field.key;
      input.dataset.index = String(i);

      const label = document.createElement("label");
      label.htmlFor = input.id;
      label.textContent = `Vehicle ${i + 1} — ${field.label}`;

      const error = document.createElement("div");
      error.className = "error";
      error.id = `error-${field.key}-${i}`;

      wrapper.append(label, input, error);
      row.appendChild(wrapper);
    });

    container.appendChild(row);
  }
}

function setError(input, message) {
  const error = document.getElementById(
    `error-${input.dataset.field}-${input.dataset.index}`
  );
  error.textContent = message;
  input.classList.toggle("invalid", Boolean(message));
  input.setAttribute("aria-invalid", message ? "true" : "false");
}

function validateInput(input) {
  const value = input.value.trim();
  const index = Number(input.dataset.index) + 1;

  if (value === "") {
    setError(input, `Vehicle ${index}: this field is required.`);
    return null;
  }

  if (input.dataset.field === "price") {
    const price = Number(value);
    if (!Number.isFinite(price)) {
      setError(input, `Vehicle ${index}: price must be a number.`);
      return null;
    }
    if (price <= 0) {
      setError(input, `Vehicle ${index}: price must be greater than 0.`);
      return null;
    }
    setError(input, "");
    return price;
  }

  setError(input, "");
  return value;
}

function collectVehicles(form) {
  const vehicles = [];
  let valid = true;

  for (let i = 0; i < NUM_VEHICLES; i++) {
    const vehicle = {};
    FIELDS.forEach((field) => {
      const input = form.querySelector(`#${field.key}-${i}`);
      const value = validateInput(input);
      if (value === null) {
        valid = false;
      } else {
        vehicle[field.key] = value;
      }
    });
    vehicles.push(vehicle);
  }

  return valid ? vehicles : null;
}

function formatPrice(price) {
  return price.toLocaleString(undefined, {
    minimumFractionDigits: 2,
    maximumFractionDigits: 2,
  });
}

function renderResult(section, vehicles) {
  let most = vehicles[0];
  let least = vehicles[0];

  vehicles.forEach((vehicle) => {
    if (vehicle.price > most.price) most = vehicle;
    if (vehicle.price < least.price) least = vehicle;
  });

  const heading = document.createElement("h2");
  heading.textContent = "Results";

  const line = (title, vehicle) => {
    const paragraph = document.createElement("p");
    const label = document.createElement("strong");
    label.textContent = `${title}: `;
    paragraph.append(
      label,
      `${vehicle.id} (${vehicle.type}) — ${formatPrice(vehicle.price)}`
    );
    return paragraph;
  };

  section.replaceChildren(
    heading,
    line("Most expensive", most),
    line("Least expensive", least)
  );
  section.hidden = false;
}

document.addEventListener("DOMContentLoaded", () => {
  const form = document.getElementById("vehicle-form");
  const container = document.getElementById("vehicle-fields");
  const result = document.getElementById("result");

  buildForm(container);

  container.addEventListener("input", (event) => {
    if (event.target instanceof HTMLInputElement) {
      validateInput(event.target);
    }
  });

  form.addEventListener("submit", (event) => {
    event.preventDefault();
    const vehicles = collectVehicles(form);

    if (!vehicles) {
      result.hidden = true;
      const firstInvalid = form.querySelector("input.invalid");
      if (firstInvalid) firstInvalid.focus();
      return;
    }

    renderResult(result, vehicles);
  });
});
