let containerStyle =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~alignItems="center",
    ~justifyContent="space-between",
    ~flexDirection="column",
    (),
  );

type state = string;

type action =
  | Input(string);

let reducer = (state, action) => {
  switch (action) {
  | Input(x) => x
  };
};

let initialState = "";

[@react.component]
let make = (~onSubmit: string => unit) => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  <form
    style=containerStyle
    onSubmit={e => {
      ReactEvent.Form.preventDefault(e);
      onSubmit(state);
    }}>
    <label htmlFor="fname">
      {ReasonReact.string("Hello friend, tell me your name...")}
    </label>
    <input
      type_="text"
      id="fname"
      name="fname"
      placeholder="Your name here"
      value=state
      onInput={e => dispatch(Input(ReactEvent.Form.target(e)##value))}
    />
    <input type_="submit" value="Let's go ->" />
  </form>;
};
