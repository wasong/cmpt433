const SELECT_MONITOR = 'SELECT_MONITOR'
const SAVE_LOGS = 'SAVE_LOGS'
const SAVE_LOG_INTERVAL_ID = 'SAVE_LOG_INTERVAL_ID'
const LOGGING = 'LOGGING'

export const selectMonitor = monitor => ({
  type: SELECT_MONITOR,
  monitor,
})

export const saveLogs = logs => ({
  type: SAVE_LOGS,
  logs,
})

export const saveLogIntervalID = logIntervalID => ({
  type: SAVE_LOG_INTERVAL_ID,
  logIntervalID,
})

export const startLogging = () => ({
  type: LOGGING,
  logging: true,
})

export const actions = {
  selectMonitor,
  saveLogs,
  saveLogIntervalID,
  startLogging,
}

const ACTION_HANDLERS = {
  [SELECT_MONITOR]: (state, { monitor }) => ({
    ...state,
    monitor,
  }),
  [SAVE_LOGS]: (state, { logs }) => ({
    ...state,
    logs: [...state.logs, logs],
  }),
  [SAVE_LOG_INTERVAL_ID]: (state, { logIntervalID }) => ({
    ...state,
    logIntervalID,
  }),
  [LOGGING]: (state, { logging }) => ({
    ...state,
    logging,
  }),
}

const initialState = {
  monitor: null,
  logIntervalID: null,
  logging: false,
  logs: [],
}

export default function reducer(state = initialState, action) {
  const handler = ACTION_HANDLERS[action.type]

  return handler ? handler(state, action) : state
}
