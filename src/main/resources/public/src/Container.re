[@react.component]
let make = (~title: string, ~children: React.element) => {
  <div className="container">
    <div className="containerTitle"> {React.string(title)} </div>
    <div className="containerContent"> children </div>
  </div>;
};
