[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ExampleStyles.style;

let makeContainer = () => {
  let container = document##createElement("div");
  let () = document##body##appendChild(container);
  container;
};

ReactDOMRe.render(<Router />, makeContainer());
