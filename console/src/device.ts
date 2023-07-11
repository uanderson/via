import { LitElement, html, customElement, property, css } from 'lit-element';

interface Status {
  wifiConnected: boolean;
  wifiSsid?: string;
}

@customElement('via-device')
export class Device extends LitElement {
  static override styles = css`
    /* Mobile First CSS */
    :host {
      display: block;
    }
    
    body {
      font-family: Arial, sans-serif;
      margin: 0;
      padding: 0;
    }
    form {
      width: 100%;
    }
    .container {
      padding: 1rem;
      box-sizing: border-box;
    }
    label,
    select,
    input {
      display: block;
      width: 100%;
    }
    label {
      margin-bottom: 0.5rem;
    }
    select,
    input {
      padding: 0.5rem;
      border: 1px solid #ccc;
      border-radius: 4px;
      font-size: 1rem;
      box-sizing: border-box;
      margin-bottom: 1rem;
    }
    button {
      margin-top: 1rem;
      padding: 0.5rem;
      background-color: #0077cc;
      color: #fff;
      border: none;
      border-radius: 4px;
      font-size: 1rem;
      cursor: pointer;
    }
    button:disabled {
      opacity: 0.5;
      cursor: not-allowed;
    }

    /* Desktop CSS */
    @media (min-width: 480px) {
      .container {
        max-width: 400px;
        margin: 2rem auto;
      }
    }
  `;

  @property({ type: String })
  selectedSsid = '';

  @property({ type: String })
  password = '';

  @property({ type: Boolean })
  disabled = false;

  @property({ type: Array })
  availableSsids: string[] = [];

  @property({ type: Object })
  status: Status = {
    wifiConnected: true
  };

  @property({ type: Boolean })
  editMode = false;

  override connectedCallback() {
    super.connectedCallback();
    this.fetchSsids();
    this.fetchStatus();
  }

  async fetchSsids() {
    const response = await fetch('/api/scan');
    const data = await response.json();

    this.availableSsids = data.reduce((arr: string[], current: string) => {
      if (!arr.includes(current)) {
        arr.push(current);
      }

      return arr;
    }, []).sort();
  }

  async fetchStatus() {
    const response = await fetch('/api/status');
    this.status = await response.json();
  }

  async handleSubmit(event: Event) {
    event.preventDefault();

    this.disabled = true;

    try {
      const response = await fetch('/api/connect', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify({
          ssid: this.selectedSsid,
          password: this.password,
        }),
      });

      if (response.ok) {
        alert('Connected successfully!');
      } else {
        throw new Error('Failed to connect.');
      }
    } catch (error) {
      alert('Not possible, dude');
    } finally {
      this.disabled = false;
    }
  }

  override render() {
    return html`
      <div class="container">
        ${this.status.wifiConnected && !this.editMode
            ? html`${this.renderStatus()}`
            : html`${this.renderWifiForm()}`}
      </div>
    `;
  }

  renderStatus() {
    return html`
      <p> 🟢 Connected to ${this.status.wifiSsid}</p>
      <button @click=${() => this.editMode = true}>Alterar</button>
    `;
  }

  renderWifiForm() {
    return html`
      <form @submit=${this.handleSubmit}>
        <label for="ssid-select">Select SSID:</label>
        <select
            id="ssid-select"
            .value=${this.selectedSsid}
            ?disabled=${this.disabled}
            @input=${(e: InputEvent) =>
                (this.selectedSsid = (e.target as HTMLSelectElement).value)}
        >
          ${this.availableSsids?.map(
              (ssid: string) => html`
                <option value=${ssid}>${ssid}</option>`
          )}
        </select>

        <label for="password-input">Senha:</label>
        <input
            id="password-input"
            type="password"
            .value=${this.password}
            ?disabled=${this.disabled}
            @input=${(e: InputEvent) =>
                (this.password = (e.target as HTMLInputElement).value)}
        />

        <button id="connect-btn" type="submit" ?disabled=${this.disabled}>
          Conectar
        </button>
      </form>
    `;
  }
}

declare global {
  interface HTMLElementTagNameMap {
    'via-device': Device;
  }
}
