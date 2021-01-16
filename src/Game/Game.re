let containerStyle =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~alignItems="center",
    ~justifyContent="space-between",
    (),
  );

let targetPics =
  [|"res/z.svg", "res/o.svg", "res/o.svg", "res/v.svg", "res/u.svg"|]
  |> Array.map(x => Some(x));
let resetTime = 10;
let noPic = "res/rect.svg";

type timer =
  | Uninitialized
  | Started(int)
  | Stopped(int, int);

type state = {
  timer,
  pics: array(option(string)),
  drag: option(int),
};

type action =
  | Drag(int)
  | Drop(int)
  | Tick;

let initialState = () => {
  {
    timer: Uninitialized,
    pics:
      (targetPics |> Belt.Array.shuffle)
      ->Belt.Array.concat(Array.init(5, _ => None)),
    drag: None,
  };
};

let tryFinishingGame = (time, state) =>
  if (Belt.Array.eq(Belt.Array.sliceToEnd(state.pics, 5), targetPics, (x, y) =>
        Belt.Option.eq(x, y, (a, b) => a == b)
      )) {
    {...state, timer: Stopped(time, resetTime)};
  } else {
    state;
  };

let movePicture = (source, target, state) => {
  let s = state.pics[source];
  state.pics[source] = state.pics[target];
  state.pics[target] = s;
  {...state, drag: None};
};

let reducer = (state, action) => {
  switch (action) {
  | Drag(index) =>
    switch (state.timer) {
    | Started(_) => {...state, drag: Some(index)}
    | _ => {...state, timer: Started(0), drag: Some(index)}
    }
  | Tick =>
    switch (state.timer) {
    | Started(t) => {...state, timer: Started(t + 1)}
    | Stopped(result, restart) =>
      if (restart > 1) {
        {...state, timer: Stopped(result, restart - 1)};
      } else {
        initialState();
      }

    | Uninitialized => state
    }
  | Drop(target) =>
    switch (state.timer, state.drag) {
    | (Started(time), Some(source)) =>
      state |> movePicture(source, target) |> tryFinishingGame(time)
    | _ => state
    }
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState());

  React.useEffect0(() => {
    let id = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(id));
  });
  <div>
    <div style=containerStyle>
      {React.string(
         switch (state.timer) {
         | Uninitialized => "Please click and drag a letter to start the game"
         | Started(t) => {j|Time: $t seconds|j}
         | Stopped(gameTime, restartTime) => {j|Congratulations, your time is: $gameTime seconds. The game will reset in $restartTime seconds|j}
         },
       )}
    </div>
    <div style=containerStyle>
      {Belt.Array.slice(state.pics, ~offset=0, ~len=5)
       |> Array.mapi((i, op) =>
            Belt.Option.mapWithDefault(op, <div />, p =>
              <img
                src=p
                draggable=true
                onDragStart={_e => dispatch(Drag(i))}
              />
            )
          )
       |> React.array}
    </div>
    <div style=containerStyle>
      {Belt.Array.sliceToEnd(state.pics, 5)
       |> Array.mapi((i, pic) =>
            Belt.Option.mapWithDefault(
              pic,
              <img
                src=noPic
                onDragOver={e => ReactEvent.Mouse.preventDefault(e)}
                onDrop={e => {
                  ReactEvent.Mouse.preventDefault(e);
                  dispatch(Drop(i + 5));
                }}
              />,
              p =>
              <img
                src=p
                draggable=true
                onDragStart={_e => dispatch(Drag(i + 5))}
                onDragOver={e => ReactEvent.Mouse.preventDefault(e)}
                onDrop={e => {
                  ReactEvent.Mouse.preventDefault(e);
                  dispatch(Drop(i + 5));
                }}
              />
            )
          )
       |> React.array}
    </div>
  </div>;
};