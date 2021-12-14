var styleFolder = './styles/';
var styles = ['first.css', 'second.css'];
styles.forEach(function (style) {
    if (style.slice(-4) === ".css") {
        var buttonContainer = document.getElementsByClassName("theme-buttons")[0];
        var placeholder = document.createElement('div');
        placeholder.innerHTML = "<button class=\"theme-button\">".concat(style.slice(0, -4), "</button>");
        var button = placeholder.firstElementChild;
        button.addEventListener("click", function (e) { switchTheme(styleFolder + style); });
        buttonContainer.appendChild(button);
    }
});
function switchTheme(theme) {
    var links = document.getElementsByTagName('link');
    for (var _i = 0, _a = links; _i < _a.length; _i++) {
        var link = _a[_i];
        if (link.rel === "stylesheet")
            link.setAttribute("href", theme);
    }
}
