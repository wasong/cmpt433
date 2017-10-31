import React, { Component } from 'react'
import PropTypes from 'prop-types'
import { connect } from 'react-redux'
import Radium from 'radium'
import RaisedButton from 'material-ui/RaisedButton'

import io from '../../../utils/socket'

const styles = {
  root: {
    overflowY: 'auto',
    height: '100%',
  },
}


class List extends Component {
  constructor(props) {
    super(props)

    this.state = {
      message: null,
    }

    io.on('commandReply', (message) => {
      this.setState({
        message,
      })
    })
  }

  handleSendData = () => {
    io.emit('prime', 'help')
  }

  render() {
    return (
      <div style={styles.root}>
        <RaisedButton label="Primary" onClick={this.handleSendData} primary />
        <div>{this.state.message}</div>
      </div>
    )
  }
}

List.propTypes = {}
List.defaultProps = {}

const mapStateToProps = state => ({
  message: state.app.message,
})

export default connect(mapStateToProps, () => ({}))(Radium(List))
