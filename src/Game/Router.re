type state = option(string);

type action =
  | SubmitUser(string);

let initialState = None;

let reducer = (state, action) => {
  switch (action) {
  | SubmitUser(u) =>
    if (String.trim(u) |> String.length > 0) {
      Some(String.trim(u));
    } else {
      None;
    }
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  switch (state) {
  | None => <Intro onSubmit={v => dispatch(SubmitUser(v))} />
  | Some(u) => <Game user=u />
  };
};
