import React, { Component } from 'react'
import { connect } from 'react-redux'
import { bindActionCreators } from 'redux'
import Radium from 'radium'

import Monitors from './Monitors'
import Featured from './Featured'
import { actions } from './dashboard.module'

const styles = {
  root: {
    display: 'flex',
  },
}

class Dashboard extends Component {
  state = {}

  render() {
    return (
      <div style={styles.root}>
        <Monitors onClick={this.props.actions.selectMonitor} />
        <Featured />
      </div>
    )
  }
}

const mapStateToProps = state => ({})
const mapDispatchToProps = dispatch => ({
  actions: bindActionCreators({ ...actions }, dispatch),
})

export default connect(mapStateToProps, mapDispatchToProps)(Radium(Dashboard))
