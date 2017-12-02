const SELECT_MONITOR = 'SELECT_MONITOR'

export const selectMonitor = monitor => ({
  type: SELECT_MONITOR,
  monitor,
})

export const actions = {
  selectMonitor,
}

const ACTION_HANDLERS = {
  [SELECT_MONITOR]: (state, { monitor }) => ({
    ...state,
    monitor,
  }),
}

const initialState = {}

export default function reducer(state = initialState, action) {
  const handler = ACTION_HANDLERS[action.type]

  return handler ? handler(state, action) : state
}
