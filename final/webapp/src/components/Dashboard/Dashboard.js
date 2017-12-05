import React, { Component } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'
import Radium from 'radium'

import socket from 'utils/socket'

import Monitors from './Monitors'
import Featured from './Featured'
import { actions } from './dashboard.module'

const styles = {
  root: {
    display: 'flex',
    flex: 1,
  },
}

class Dashboard extends Component {
  state = {}

  // componentDidMount = () => {
  //   if (!this.props.logIntervalID) {
  //     const logIntervalID = setInterval(() => {
  //       socket.emit('prime', 'help')
  //     }, 1000)
  //
  //     this.props.actions.saveLogIntervalID(logIntervalID)
  //
  //     if (!this.props.logging) socket.on('default', this.handleLogger)
  //     this.props.actions.startLogging()
  //   }
  // }
  //
  // componentWillUnmount = () => {
  //   socket.close()
  // }

  handleLogger = (logs) => {
    this.props.actions.saveLogs(logs)
  }

  render() {
    const { logs } = this.props
    return (
      <div style={styles.root}>
        <Monitors onClick={actions.selectMonitor} />
        <Featured
          logs={logs}
        />
      </div>
    )
  }
}

const mapStateToProps = state => ({
  logs: state.dashboard.logs,
  logging: state.dashboard.logging,
  logIntervalID: state.dashboard.logIntervalID,
})
const mapDispatchToProps = dispatch => ({
  actions: bindActionCreators({ ...actions }, dispatch),
})

export default connect(mapStateToProps, mapDispatchToProps)(Radium(Dashboard))
