// ------------------------------------
// Constants
// ------------------------------------
const TEST_REDUCER = 'TEST_REDUCER'

// ------------------------------------
// Actions
// ------------------------------------
export const testReducer = () => ({
  type: TEST_REDUCER,
})

export const actions = {
  testReducer,
}

// ------------------------------------
// Action Handlers
// ------------------------------------
const ACTION_HANDLERS = {
  [TEST_REDUCER]: state => ({
    ...state,
  }),
}

// ------------------------------------
// Reducer
// ------------------------------------
const initialState = {}

export default function reducer(state = initialState, action) {
  const handler = ACTION_HANDLERS[action.type]

  return handler ? handler(state, action) : state
}
