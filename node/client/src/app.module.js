// ------------------------------------
// Constants
// ------------------------------------
const SAVE_MESSAGE = 'SAVE_MESSAGE'

// ------------------------------------
// Actions
// ------------------------------------

export const saveMessageSuccess = message => ({
  type: SAVE_MESSAGE,
  message,
})

export const saveMessage = message => (dispatch) => {
  dispatch(saveMessageSuccess(message))
}

export const actions = {
  saveMessage,
}

// ------------------------------------
// Action Handlers
// ------------------------------------
const ACTION_HANDLERS = {
  [SAVE_MESSAGE]: (state, { message }) => ({
    ...state,
    message,
  }),
}

// ------------------------------------
// Reducer
// ------------------------------------
const initialState = {
  message: null,
}

export default function reducer(state = initialState, action) {
  const handler = ACTION_HANDLERS[action.type]

  return handler ? handler(state, action) : state
}
