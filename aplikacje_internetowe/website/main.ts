const styleFolder = './styles/'
const styles = ['first.css', 'second.css']

styles.forEach(style => {
    if (style.slice(-4) === ".css") {
        var buttonContainer = document.getElementsByClassName("theme-buttons")[0];
        const placeholder = document.createElement('div');
        placeholder.innerHTML = `<button class="theme-button">${style.slice(0, -4)}</button>`;
        var button = placeholder.firstElementChild as HTMLButtonElement;
        button.addEventListener("click", (e: Event) => { switchTheme(styleFolder + style) });
        buttonContainer.appendChild(button);
    }
})


function switchTheme(theme: string) {
    var links = document.getElementsByTagName('link');
    for (let link of links as any)
        if (link.rel === "stylesheet")
            link.setAttribute("href", theme)
}